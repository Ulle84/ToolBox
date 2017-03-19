#ifndef OPTIONS_H
#define OPTIONS_H

#include <QStringList>
#include <QString>

class Options
{
  public:
    Options();

    void parseCommandLineArguments(int argc, char* argv[]);
    void enableAll(bool enabled = true);
    void print();
    bool extensionAllowed(const QString& fileName);

    bool m_addMPrefixToMembers = false;
    bool m_beautify = false;
    bool m_cleanElementInitializiers = false;
    bool m_doBlockCodeFormatting = false;
    bool m_includeSubdirectories = false;
    bool m_removeDoubleEmptyLines = true;
    bool m_removeUnnecessarySpaces = false;
    bool m_removeEmptyLinesAfterOpeningBracket = true;
    bool m_removeEmptyLinesBeforeClosingBracket = true;
    bool m_removeLineBreaksInsideParentheses = false;
    bool m_removeUnnecessaryStuff = false;
    bool m_runAStyle = true;
    bool m_cleanComments = false;



    QStringList m_arguments;
    QStringList m_files;
    QStringList m_directories;
    QStringList m_excludedFiles;
    QStringList m_excludedDirectories;
    QStringList m_allowedExtensions;

    QString m_checkSumsFileName;

  private:
    void applyCommandLineArguments();
    void convertSlashes();
}
;

#endif
