package djinni

import djinni.ast._
import djinni.generatorTools._
import djinni.meta._

class SwiftMarshal(spec: Spec) extends Marshal(spec) {
  override def typename(name: String, ty: TypeDef): String = idSwift.ty(name)

  override def typename(tm: MExpr): String = ???

  override def fqTypename(tm: MExpr): String = ???

  override def paramType(tm: MExpr): String = getSwiftBridgingType(tm).swift

  override def fqParamType(tm: MExpr): String = ???

  override def returnType(ret: Option[TypeRef]): String = ???

  override def fqReturnType(ret: Option[TypeRef]): String = ???

  override def fieldType(tm: MExpr): String = ???

  override def fqFieldType(tm: MExpr): String = getSwiftBridgingType(tm).swift

  override def deprecatedAnnotation(deprecated: Option[Deprecated]): Option[String] = {
    deprecated match {
      case Some(value) => Some(s"@available(*, deprecated, message: ${value.messages})")
      case None => None
    }
  }

  def getSwiftBridgingType(tm: MExpr): SwiftBridgingType = {

    def find(tm: MExpr, downcast: Boolean = false): SwiftBridgingType = {
      val base: SwiftBridgingType = tm.base match {
        case opaque: MOpaque => opaque match {
          case p: MPrimitive =>
            if (downcast)
              SwiftBridgingType(wrapper = "NSNumber", swift = p.swiftName, typeCastingOperator = " as ")
            else
              SwiftBridgingType(wrapper = p.swiftName, swift = p.swiftName)
          case meta.MString => SwiftBridgingType(wrapper = "String", swift = "String")
          case meta.MDate => SwiftBridgingType(wrapper = "Date", swift = "Date")
          case meta.MBinary => SwiftBridgingType(wrapper = "Data", swift = "Data")
          case meta.MOptional =>
            // recursive to find the correct arg type
            val arg = tm.args.head

            val downcast = arg.base match {
              case opaque: MOpaque => opaque match {
                // Swift primitive can not be represent in Objc -> We need to uses the downcast value.
                case _: MPrimitive => true
                case _ => false
              }
              case d: MDef => d.defType match {
                case meta.DEnum =>
                  true
                case _ => false
              }
              case _ => false
            }

            val bridgingType = find(arg, downcast)
            SwiftBridgingType(wrapper = s"${bridgingType.wrapper}?", swift = s"${bridgingType.swift}?", downcast = downcast,
              typeCastingOperator = bridgingType.typeCastingOperator)
          case meta.MList =>
            val arg = tm.args.head
            val bridgingType = find(arg)
            SwiftBridgingType(wrapper = s"Array<${bridgingType.swift}>", swift = s"Array<${bridgingType.swift}>")
          case meta.MSet =>
            val arg = tm.args.head
            val bridgingType = find(arg)
            SwiftBridgingType(wrapper = s"Set<${bridgingType.swift}>", swift = s"Set<${bridgingType.swift}>")
          case meta.MMap =>
            val key = tm.args.head
            val value = tm.args.last
            val keyBridgingType = find(key)
            val valueBridgingType = find(value)

            val bridgingType = s"Dictionary<${keyBridgingType.swift}, ${valueBridgingType.swift}>"
            SwiftBridgingType(wrapper = bridgingType, swift = bridgingType)

          case meta.MJson =>
            val bridgingType = s"Dictionary<String, Any>"
            SwiftBridgingType(wrapper = bridgingType, swift = bridgingType)
        }
        case d: MDef => d.defType match {
          case meta.DEnum =>
            if (downcast)
              SwiftBridgingType(wrapper = "NSNumber", swift = idSwift.ty(d.name), typeCastingOperator = "?.rawValue as ")
            else
              SwiftBridgingType(wrapper = idSwift.ty(d.name), swift = idSwift.ty(d.name))
          case meta.DRecord =>
            val objcWrapper = idObjc.ty(d.name)
            val swift = idSwift.ty(d.name)
            SwiftBridgingType(wrapper = objcWrapper, swift = swift)
          case meta.DInterface => throw new AssertionError("Parameter should not happen at Obj-C top level")
        }
        case MExtern(name, numParams, defType, body, cpp, objc, objcpp, java, jni) => throw new AssertionError("Parameter should not happen at Obj-C top level")
        case _ => throw new AssertionError("Parameter should not happen at Obj-C top level")
      }
      base
    }

    find(tm = tm)
  }

}