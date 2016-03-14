#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QQuickTextDocument>

class SyntaxHighlighter : public QSyntaxHighlighter {
Q_OBJECT
public:
  Q_PROPERTY(QQuickTextDocument* document READ quickTextDocument WRITE setQuickTextDocument)


  struct HighlightingRule {
    QRegExp pattern;
    QTextCharFormat format;
  };

  SyntaxHighlighter( QTextDocument* parent = 0x0 );

  void                        addHighlightRule( const HighlightingRule& rule );
  void                        addHighlightRule( const QRegExp& pattern, const QTextCharFormat& format );
  void                        addKeyword( const QString& keyword );
  void                        addKeywords( const QStringList& keywords );

  void                        setKeywordFormat( const QTextCharFormat& format );
  void                        setMultilineCommentEndExp( const QRegExp& exp );
  void                        setMultilineCommentFormat( const QTextCharFormat& format );
  void                        setMultilineCommentStartExp( const QRegExp& exp );
  void                        setQuotationExp( const QRegExp& exp );
  void                        setQuotationFormat( const QTextCharFormat& format );
  void                        setSingleLineCommentExp( const QRegExp& exp );
  void                        setSingleLineCommentFormat( const QTextCharFormat& format );

  void                        updateFormatting();

  QQuickTextDocument*         quickTextDocument() const;
  Q_INVOKABLE void            setQuickTextDocument(QQuickTextDocument* document);

protected:
  void                        highlightBlock(const QString &text);

private:

  QVector<HighlightingRule>   _hightlighting_rules;

  QRegExp                     _multi_line_comment_start_exp;
  QRegExp                     _multi_line_comment_end_exp;
  QRegExp                     _single_line_comment_exp;
  QRegExp                     _quotation_exp;
  QRegExp                     _function_exp;

  QTextCharFormat             _keyword_format;
  QTextCharFormat             _single_line_comment_format;
  QTextCharFormat             _multi_line_comment_format;
  QTextCharFormat             _quotation_format;
  QTextCharFormat             _function_format;

  QStringList                 _keywords;

  QQuickTextDocument*         _document;




}; // END class SyntaxHighlighter


#endif // SYNTAXHIGHLIGHTER_H
