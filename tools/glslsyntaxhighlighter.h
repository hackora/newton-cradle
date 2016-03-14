#ifndef GLSLSYNTAXHIGHLIGHTER_H
#define GLSLSYNTAXHIGHLIGHTER_H

// local
#include "syntaxhighlighter.h"

class GLSLSyntaxHighlighter : public SyntaxHighlighter {
  Q_OBJECT
public:
  GLSLSyntaxHighlighter( QTextDocument* parent = 0x0 );

}; // END class GLSLSyntaxHighlighter


#endif // GLSLSYNTAXHIGHLIGHTER_H
