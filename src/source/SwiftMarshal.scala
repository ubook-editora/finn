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
            case m => f(arg, true) match {
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
              case DEnum => if (needRef) ("NSNumber", true) else (idSwift.ty(d.name), false)
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
}