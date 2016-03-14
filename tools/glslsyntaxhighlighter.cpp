
// Qt
#include <QStringList>

// header
#include "glslsyntaxhighlighter.h"

GLSLSyntaxHighlighter::GLSLSyntaxHighlighter(QTextDocument *parent) : SyntaxHighlighter(parent) {


  QStringList keywords;

  // Types
  keywords
      << "void" << "bool" << "int" << "uint" << "float" << "double"
      << "vec2" << "vec3" << "vec4"
      << "dvec2" << "dvec3" << "dvec4"
      << "bvec2" << "bvec3" << "bvec4"
      << "ivec2" << "ivec3" << "ivec4"
      << "uvec2" << "uvec3" << "uvec4"
      << "mat2" << "mat3" << "mat4"
      << "mat2x2" << "mat2x3" << "mat2x4"
      << "mat3x2" << "mat3x3" << "mat3x4"
      << "mat4x2" << "mat4x3" << "mat4x4"
      << "dmat2" << "dmat3" << "dmat4"
      << "dmat2x2" << "dmat2x3" << "dmat2x4"
      << "dmat3x2" << "dmat3x3" << "dmat3x4"
      << "dmat4x2" << "dmat4x3" << "dmat4x4";

      // More types missing


  // Qualifiers
  keywords
      << "const" << "in" << "centroid in" << "sample in" << "out" << "centroid out" << "sample out"
      << "uniform" << "patch in" << "patch out";

      // deprecated qualifiers missing



  addKeywords( keywords );

  updateFormatting();


}
