
// header
#include "syntaxhighlighter.h"

// qt
#include <QQuickTextDocument>

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter( parent ) {

  QColor text_color = QColor( Qt::green ).darker( 200 );

  _keyword_format.setForeground(Qt::darkYellow);

  _quotation_format.setForeground(text_color);
  _quotation_exp = QRegExp("\".*\"");

  _function_format.setFontItalic(true);
  _function_format.setForeground(Qt::blue);
  _function_exp = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");

  _single_line_comment_format.setForeground( text_color );
  _single_line_comment_exp = QRegExp("//[^\n]*");

  _multi_line_comment_format.setForeground(text_color );
  _multi_line_comment_start_exp = QRegExp("/\\*");
  _multi_line_comment_end_exp = QRegExp("\\*/");

}

void SyntaxHighlighter::addHighlightRule(const HighlightingRule &rule) {

  _hightlighting_rules.append( rule );
}

void SyntaxHighlighter::addHighlightRule(const QRegExp &pattern, const QTextCharFormat &format) {

  HighlightingRule rule;

  rule.pattern = pattern;
  rule.format = format;

  _hightlighting_rules.append( rule );
}

void SyntaxHighlighter::addKeyword(const QString &keyword) {

  _keywords.append( keyword );
}

void SyntaxHighlighter::addKeywords(const QStringList &keywords) {

  _keywords.append( keywords );
}

void SyntaxHighlighter::highlightBlock(const QString &text) {

  foreach (const HighlightingRule &rule, _hightlighting_rules ) {

    QRegExp expression( rule.pattern );
    int index = expression.indexIn( text );

    while (index >= 0) {

      int length = expression.matchedLength();
      setFormat( index, length, rule.format );
      index = expression.indexIn( text, index + length );
    }
  }
  setCurrentBlockState(0);

  int start_index = 0;
  if ( previousBlockState() != 1 )
    start_index = _multi_line_comment_start_exp.indexIn( text );

  while (start_index >= 0) {

    int end_index = _multi_line_comment_end_exp.indexIn( text, start_index );
    int comment_length;

    if( end_index == -1 ) {

      setCurrentBlockState(1);
      comment_length = text.length() - start_index;
    }
    else
      comment_length = end_index - start_index + _multi_line_comment_end_exp.matchedLength();

    setFormat(start_index, comment_length, _multi_line_comment_format );
    start_index = _multi_line_comment_start_exp.indexIn(text, start_index + comment_length);
  }
}

QQuickTextDocument*SyntaxHighlighter::quickTextDocument() const {

  return _document;
}

void SyntaxHighlighter::setQuickTextDocument(QQuickTextDocument* document) {

  _document = document;
  setDocument(_document->textDocument());
}

void SyntaxHighlighter::setKeywordFormat(const QTextCharFormat &format) {

  _keyword_format = format;
}

void SyntaxHighlighter::setMultilineCommentEndExp( const QRegExp& exp ) {

  _multi_line_comment_end_exp = exp;
}

void SyntaxHighlighter::setMultilineCommentFormat( const QTextCharFormat& format ) {

  _multi_line_comment_format = format;
}

void SyntaxHighlighter::setMultilineCommentStartExp( const QRegExp& exp ) {

  _multi_line_comment_start_exp = exp;
}

void SyntaxHighlighter::setQuotationExp( const QRegExp& exp ) {

  _quotation_exp = exp;
}

void SyntaxHighlighter::setQuotationFormat( const QTextCharFormat& format ) {

  _quotation_format = format;
}

void SyntaxHighlighter::setSingleLineCommentExp( const QRegExp& exp ) {

  _single_line_comment_exp = exp;
}

void SyntaxHighlighter::setSingleLineCommentFormat( const QTextCharFormat& format ) {

  _single_line_comment_format = format;
}

void SyntaxHighlighter::updateFormatting() {

  HighlightingRule rule;

  foreach( const QString &keyword, _keywords ) {

    rule.pattern = QRegExp(QString("\\b%1\\b").arg(keyword));
    rule.format = _keyword_format;
    _hightlighting_rules.append(rule);
  }

  rule.pattern = _single_line_comment_exp;
  rule.format = _single_line_comment_format;
  _hightlighting_rules.append(rule);

  rule.pattern = _quotation_exp;
  rule.format = _quotation_format;
  _hightlighting_rules.append(rule);

  rule.pattern = _function_exp;
  rule.format = _function_format;
  _hightlighting_rules.append(rule);
}























