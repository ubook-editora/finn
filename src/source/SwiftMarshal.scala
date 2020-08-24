package djinni

import djinni.ast._
import djinni.generatorTools._
import djinni.meta._
import djinni.writer.IndentWriter

class SwiftMarshal(spec: Spec) extends Marshal(spec) {
  override def typename(name: String, ty: TypeDef): String = idSwift.ty(name)

  override def typename(tm: MExpr): String = ???

  override def fqTypename(tm: MExpr): String = ???

  override def paramType(tm: MExpr): String = toSwiftType(tm, false)._1

  override def fqParamType(tm: MExpr): String = ???

  override def returnType(ret: Option[TypeRef]): String = ???

  override def fqReturnType(ret: Option[TypeRef]): String = ???

  override def fieldType(tm: MExpr): String = ???

  override def fqFieldType(tm: MExpr): String = toSwiftType(tm, false)._1

  override def deprecatedAnnotation(deprecated: Option[Deprecated]): Option[String] = {
    deprecated match {
      case Some(value) => Some(s"@available(*, deprecated, message: ${value.messages})")
      case None => None
    }
  }

  def nullability(tm: MExpr): Option[String] = {
    val nonnull = Some("")
    val nullable = Some("?")
    val interfaceNullity = if (spec.cppNnType.nonEmpty) nonnull else nullable
    tm.base match {
      case MOptional => nullable
      case MPrimitive(_, _, _, _, _, _, _, _, _) => None
      case d: MDef => d.defType match {
        case DEnum => None
        case DInterface => interfaceNullity
        case DRecord => nonnull
      }
      case e: MExtern => e.defType match {
        case DEnum => None
        case DInterface => interfaceNullity
        case DRecord => if (e.objc.pointer) nonnull else None
      }
      case _ => nonnull
    }
  }

  def toBoxedParamType(tm: MExpr): String = {
    val (name, needRef) = toSwiftType(tm, false)
    name
  }

  def toBoxedParamType_2(tm: MExpr): String = {
    val (name, needRef) = toSwiftType(tm, true)
    name
  }

  def swiftForceCast(tm: MExpr): Option[(String, String)] = {
    def args(tm: MExpr) = if (tm.args.isEmpty) "" else tm.args.map(toBoxedParamType).mkString("<", ", ", ">")

    def f(tm: MExpr, needRef: Boolean): Option[(String, String)] = {
      tm.base match {
        case MOptional =>
          // We use "nil" for the empty optional.
          assert(tm.args.size == 1)
          val arg = tm.args.head
          arg.base match {
            case MOptional => throw new AssertionError("nested optional?")
            case _ => f(arg, needRef = false) match {
              case Some(x) => Some(x._1 + "?", x._2 + "?")
              case None => None
            }
          }
        case o =>
          val base = o match {
            case p: MPrimitive => if (needRef) None else Some(p.objcBoxed, p.swiftName)
            case MOptional => throw new AssertionError("optional should have been special cased")
//            case MString => Some("NSString", "String")
//            case MDate => Some("Date", "true")
//            case MBinary => Some("Data", "true")
            case MList => {
              val arg = tm.args.head
              f(arg, needRef = false) match {
                case Some(x) => Some(s"Array<${x._1}>", s"Array<${x._2}>")
                case None => None
              }
            }
            case MSet => {
              val arg = tm.args.head
              f(arg, needRef = false) match {
                case Some(x) => Some(s"Set<${x._1}>", s"Set<${x._2}>")
                case None => None
              }
            }
            case MMap => {
              val keyType = f(tm.args.head, needRef = false) match {
                case Some(x) => s"${x._1}"
                case None => s"${toSwiftType(tm.args.head, needRef = false)._1}"
              }

              val valueType = f(tm.args(1), needRef = true) match {
                case Some(x) => s"${x._1}"
                case None => s"${toSwiftType(tm.args(1), needRef = true)._1}"
              }

              if (keyType.isEmpty || valueType.isEmpty) None
              else {
                Some(s"Dictionary<$keyType, $valueType>", s"Dictionary<${keyType}, ${valueType}>")
              }
            }
            case d: MDef => d.defType match {
              case DEnum => if (needRef) None else Some(s"NSInteger" , s"${idSwift.ty(d.name)}")
              case DRecord => Some(idSwift.ty(d.name), "true")
              case DInterface =>
                val ext = d.body.asInstanceOf[Interface].ext
                if (!ext.objc) Some(idSwift.ty(d.name), "true")
                else Some(s"id<${idSwift.ty(d.name)}>", "false")
            }
            case e: MExtern => e.body match {
              case i: Interface => if(i.ext.objc) Some(s"id<${e.objc.typename}>", "false") else Some(e.objc.typename, "true")
              case _ => if(needRef) Some(e.objc.boxed, "true") else Some(e.objc.typename," e.objc.pointer")
            }
            case _ => None
          }
          base
      }
    }

    f(tm, needRef = false)
  }

  def toSwiftWrapperType(tm: MExpr): String = {
    def args(tm: MExpr) = if (tm.args.isEmpty) "" else tm.args.map(toBoxedParamType).mkString("<", ", ", ">")

    def f(tm: MExpr, needRef: Boolean): (String, Boolean) = {
      tm.base match {
        case MOptional =>
          // We use "nil" for the empty optional.
          assert(tm.args.size == 1)
          val arg = tm.args.head
          arg.base match {
            case MOptional => throw new AssertionError("nested optional?")
            case _ => f(arg, needRef = true) match {
              case (x, y) =>
                (x + "?", y)
            }
          }
        case o =>
          val base = o match {
            case p: MPrimitive => if (needRef) (p.objcBoxed, true) else (p.swiftName, false)
            case MString => ("String", true)
            case MDate => ("Date", true)
            case MBinary => ("Data", true)
            case MOptional => throw new AssertionError("optional should have been special cased")
            case MList => ("Array" + args(tm), true)
            case MSet => ("Set" + args(tm), true)
            case MMap => ("Dictionary" + args(tm), true)
            case d: MDef => d.defType match {
              case DEnum => if (needRef) ("NSInteger", true) else (idSwift.ty(d.name), false)
              case DRecord => (idSwift.ty(d.name), true)
              case DInterface =>
                val ext = d.body.asInstanceOf[Interface].ext
                if (!ext.objc)
                  (idSwift.ty(d.name), true)
                else
                  (s"id<${idSwift.ty(d.name)}>", false)
            }
            case e: MExtern => e.body match {
              case i: Interface => if(i.ext.objc) (s"id<${e.objc.typename}>", false) else (e.objc.typename, true)
              case _ => if(needRef) (e.objc.boxed, true) else (e.objc.typename, e.objc.pointer)
            }
            case _ => throw new AssertionError("Parameter should not happen at Obj-C top level")
          }
          base
      }
    }
    f(tm, false)
  }._1

  private def toSwiftType(tm: MExpr, needRef: Boolean): (String, Boolean) = {
    def args(tm: MExpr) = if (tm.args.isEmpty) "" else tm.args.map(toBoxedParamType).mkString("<", ", ", ">")
    def f(tm: MExpr, needRef: Boolean): (String, Boolean) = {
      tm.base match {
        case MOptional =>
          // We use "nil" for the empty optional.
          assert(tm.args.size == 1)
          val arg = tm.args.head
          arg.base match {
            case MOptional => throw new AssertionError("nested optional?")
            case m => f(arg, false) match {
              case (x, y) =>
                (x + "?", y)
            }
          }
        case o =>
          val base = o match {
            case p: MPrimitive => if (needRef) (p.objcBoxed, true) else (p.swiftName, false)
            case MString => ("String", true)
            case MDate => ("Date", true)
            case MBinary => ("Data", true)
            case MOptional => throw new AssertionError("optional should have been special cased")
            case MList => ("Array" + args(tm), true)
            case MSet => ("Set" + args(tm), true)
            case MMap => ("Dictionary" + args(tm), true)
            case d: MDef => d.defType match {
              case DEnum => if (needRef) ("NSInteger", true) else (idSwift.ty(d.name), false)
              case DRecord => (idSwift.ty(d.name), true)
              case DInterface =>
                val ext = d.body.asInstanceOf[Interface].ext
                if (!ext.objc)
                  (idSwift.ty(d.name), true)
                else
                  (s"id<${idSwift.ty(d.name)}>", false)
            }
            case e: MExtern => e.body match {
              case i: Interface => if(i.ext.objc) (s"id<${e.objc.typename}>", false) else (e.objc.typename, true)
              case _ => if(needRef) (e.objc.boxed, true) else (e.objc.typename, e.objc.pointer)
            }
            case _ => throw new AssertionError("Parameter should not happen at Obj-C top level")
          }
          base
      }
    }
    f(tm, needRef)
  }

  def getTypeCastingKeyword(tm: MExpr): String = {
    tm.base match {
      case d: MDef => d.defType match {
        case meta.DEnum => ".rawValue as "
        case _ =>" as "
      }
      case _ => " as "
    }
  }

  def getSwiftBridgingType(tm: MExpr): SwiftBridgingType = {

    def find(tm: MExpr, downcast: Boolean = false): SwiftBridgingType = {
      val base: SwiftBridgingType = tm.base match {
        case opaque: MOpaque => opaque match {
          case p: MPrimitive =>
            var wrapper = p.swiftName
            if (downcast) wrapper = "NSNumber"
            SwiftBridgingType(wrapper = wrapper, swift = p.swiftName)
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
                case meta.DEnum => throw new AssertionError("Enum should not define as optional")
                case _ => false
              }
              case _ => false
            }

            val bridgingType = find(arg, downcast)
            SwiftBridgingType(wrapper = s"${bridgingType.wrapper}?", swift = s"as? ${bridgingType.swift}", downcast = downcast)
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

          case meta.MJson => throw new AssertionError("Parameter should not happen at Obj-C top level")
        }
        case d: MDef => d.defType match {
          case meta.DEnum =>
            SwiftBridgingType(wrapper = idSwift.ty(d.name), swift = idSwift.ty(d.name))
          case meta.DInterface => throw new AssertionError("Parameter should not happen at Obj-C top level")
          case meta.DRecord =>
            val objcWrapper = idObjc.ty(d.name)
            val swift = idSwift.ty(d.name)
            SwiftBridgingType(wrapper = objcWrapper, swift = swift)
        }
        case MExtern(name, numParams, defType, body, cpp, objc, objcpp, java, jni) => throw new AssertionError("Parameter should not happen at Obj-C top level")
        case _ => throw new AssertionError("Parameter should not happen at Obj-C top level")
      }
      base
    }

    find(tm = tm)
  }




}