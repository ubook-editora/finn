package djinni

import djinni.ast._
import djinni.generatorTools.{DeclRef, IdentStyle, ImportRef, SkipFirst, Spec, q}
import djinni.meta._
import djinni.writer.IndentWriter

import scala.collection.mutable

class SwiftGenerator(spec: Spec) extends ObjcGenerator(spec) {
  private val swiftMarshal = new SwiftMarshal(spec)

  override def writeObjcFile(fileName: String, origin: String, refs: Iterable[String], f: IndentWriter => Unit): Unit = {
    createFile(spec.swiftOutFolder.get, fileName, (w: IndentWriter) => {
      w.wl("// AUTOGENERATED FILE - DO NOT MODIFY!")
      w.wl("// This file generated by Djinni from " + origin)
      w.wl
      if (refs.nonEmpty) {
        // Ignore the ! in front of each line; used to put own headers to the top
        // according to Objective-C style guide
        refs.foreach(s => w.wl(if (s.charAt(0) == '!') s.substring(1) else s))
        w.wl
      }
      f(w)
    })
  }

  def writeAlignedSwiftCall(w: IndentWriter, call: String, params: Seq[Field], end: String, f: Field => (String, String)) = {
    w.w(call)
    val skipFirst = new SkipFirst
    params.foreach(p => {
      val (name, value) = f(p)
      skipFirst {
        w.wl(",")
        w.w(" " * math.max(0, call.length() - name.length))
      }
      w.w(name + ":" + value)
    })
    w.w(end)
  }

  def writeSwiftFile(fileName: String, origin: String, refs: Iterable[String], f: IndentWriter => Unit) {
    createFile(spec.swiftOutFolder.get, s"${idSwift.ty(fileName)}.swift", (w: IndentWriter) => {
      w.wl("// AUTOGENERATED FILE - DO NOT MODIFY!")
      w.wl("// This file generated by Djinni from " + origin)
      w.wl
      if (refs.nonEmpty) {
        // Ignore the ! in front of each line; used to put own headers to the top
        // according to Objective-C style guide
        refs.foreach(s => w.wl(if (s.charAt(0) == '!') s.substring(1) else s))
        w.wl
      }
      f(w)
    })
  }
  override def generateEnum(origin: String, ident: Ident, doc: Doc, e: Enum, deprecated: Option[Deprecated]): Unit = {
    var header: mutable.Set[String] = mutable.TreeSet[String]()
    header.add("import Foundation")

    writeSwiftFile(ident, origin = origin, header, w => {
      writeDoc(w, doc)
      swiftMarshal.deprecatedAnnotation(deprecated)
      w.w(s"@objc public enum ${swiftMarshal.typename(ident, e)} : Int").braced {
        var shift = -1
        for (o <- normalEnumOptions(e)) {
          writeDoc(w, o.doc)
          swiftMarshal.deprecatedAnnotation(o.deprecated).foreach(w.wl)
          if (o.value != None) {
            val constValue = o.value match {
              case Some(i) => i
            }
            shift = (constValue.toString.toInt);
          } else {
            shift = shift + 1;
          }
          w.wl(s"case ${idSwift.enum(o.ident)} = $shift")
        }
      }
    })
  }

  override def generateRecord(origin: String, ident: Ident, doc: Doc, params: Seq[TypeParam], r: Record, deprecated: Option[Deprecated], idl: Seq[TypeDecl]): Unit = {
    var header: mutable.Set[String] = mutable.TreeSet[String]()
    header.add("import Foundation")

    val superRecord = getSuperRecord(idl, r)
    val superFields: Seq[Field] = superRecord match {
      case None => Seq.empty
      case Some(value) => value.fields
    }
    val (superClass, firstInitializerArg) = superRecord match {
      case None =>
        ("NSObject", if (r.fields.isEmpty) "" else IdentStyle.camelUpper("with_" + r.fields.head.ident.name))
      case Some(value) =>
        ((if (r.ext.objc) spec.objcExtendedRecordIncludePrefix else spec.objcIncludePrefix) + swiftMarshal.typename(value.ident, value.record),
          if (r.fields.isEmpty) "" else IdentStyle.camelUpper("with_" + value.fields.head.ident.name)
        )
    }

    writeSwiftFile(ident, origin = origin, header, w => {
      writeDoc(w, doc)
      swiftMarshal.deprecatedAnnotation(deprecated).foreach(w.wl)

      w.w(s"@objc public class ${swiftMarshal.typename(ident, r)} : $superClass").braced {

        // ----------- GENERATE FIELDS
        def writeRecordFields(field: Seq[Field]): Unit = {
          for (f <- r.fields) {
            w.wl
            writeDoc(w, f.doc)
            val readonly = if (f.modifiable) "var" else "let"
            w.wl(s"@objc public $readonly ${idSwift.field(f.ident)} : ${swiftMarshal.fqFieldType(f.ty)}")
          }
          w.wl
        }

        writeRecordFields(r.fields)

        // ----------- GENERATE CONSTRUCTOR
        def writeRecordConstructor(): Unit = {
          val decl = s"@objc public init("
          writeAlignedSwiftCall(w, decl, superFields ++ r.fields, "", f => (idSwift.field(f.ident), s"${swiftMarshal.paramType(f.ty)}"))
          w.w(")")braced {
            // Write record fields
            for (f <- r.fields) {
              w.wl(s"self.${idSwift.field(f.ident)} = ${idSwift.local(f.ident)}")
            }

            // Write super record
            if (superFields.nonEmpty) {
              w.w("super.init(")
              val skipFirst = SkipFirst()
              for (f <- superFields) {
                skipFirst {
                  w.w(", ")
                }
                w.w(s"${idJava.local(f.ident)}: ${idJava.local(f.ident)}")
              }
              w.wl(")")
            }
          }
        }
        writeRecordConstructor()
      }
    })
  }

  class SwiftObjcRefs() {
    var body: mutable.Set[String] = mutable.TreeSet[String]()
    var header: mutable.Set[String] = mutable.TreeSet[String]()

    def find(ty: TypeRef) {
      find(ty.resolved)
    }

    def find(tm: MExpr) {
      tm.args.foreach(find)
      find(tm.base)
    }

    def find(m: Meta): Unit = for (r <- marshal.references(m)) r match {
      case ImportRef(arg) => header.add("#import " + arg)
      case DeclRef(decl, _) => header.add(decl)
    }
  }

  /**
    * Generate Interface
    */
  override def generateInterface(origin: String, ident: Ident, doc: Doc, typeParams: Seq[TypeParam], i: Interface, deprecated: Option[Deprecated]): Unit = {
    val refs = new SwiftObjcRefs()

    val self = marshal.typename(ident, i)
    refs.header.add("#import <Foundation/Foundation.h>")

    i.methods.foreach(m => {
      m.params.foreach(p => {
        printf(s"=====> ${p.ident.name}")
      })
      m.ret.foreach(p => {
        refs.header.add(s"@class ${marshal.typename(p.expr.ident.name, i)};")
      })
    })

    writeObjcFile(marshal.headerName(ident), origin, refs.header, w => {
      for (c <- i.consts if marshal.canBeConstVariable(c)) {
        writeDoc(w, c.doc)
        w.w(s"extern ")
        writeObjcConstVariableDecl(w, c, self)
        w.wl(s";")
      }
      w.wl
      writeDoc(w, doc)
      marshal.deprecatedAnnotation(deprecated).foreach(w.wl)
      if (spec.objcSupportSwiftName) {
        val swiftName = self.replace(spec.objcTypePrefix, "")
        w.wl(s"NS_SWIFT_NAME($swiftName)")
      }

      if (i.ext.objc) {
        w.wl(s"@protocol $self")
      } else {
        w.wl(s"@interface $self : NSObject")
        w.wl
        w.wl(s"- (nonnull instancetype)init NS_UNAVAILABLE;")
      }
      for (m <- i.methods) {
        w.wl
        writeMethodDoc(w, m, idObjc.local)
        writeObjcFuncDecl(m, w)
        marshal.deprecatedAnnotation(m.deprecated).foreach(w.wl)
        w.wl(";")
      }
      for (c <- i.consts if !marshal.canBeConstVariable(c)) {
        w.wl
        writeDoc(w, c.doc)
        writeObjcConstMethDecl(c, w)
      }
      w.wl
      w.wl("@end")
    })
  }
}