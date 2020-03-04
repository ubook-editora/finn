//package djinni
//
//import djinni.ast._
//import djinni.generatorTools._
//import djinni.meta._
//
//class SwiftMarshal(spec: Spec) extends Marshal(spec) {
//  override def typename(name: String, ty: TypeDef): String = ???
//
//  override def typename(tm: MExpr): String = ???
//
//  override def fqTypename(tm: MExpr): String = ???
//
//  override def paramType(tm: MExpr): String = ???
//
//  override def fqParamType(tm: MExpr): String = ???
//
//  override def returnType(ret: Option[TypeRef]): String = ???
//
//  override def fqReturnType(ret: Option[TypeRef]): String = ???
//
//  override def fieldType(tm: MExpr): String = ???
//
//  override def fqFieldType(tm: MExpr): String = ???
//}