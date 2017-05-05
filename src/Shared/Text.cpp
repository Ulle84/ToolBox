#include <vector>

#include "CustomTypes.h"
#include "Text.h"

namespace Text
{
  bool indentColumns(QStringList& input, const QString& alignments, QChar seperator)
  {
    int numberOfColumns = alignments.size();

    std::vector<uint> columnWidths;
    columnWidths.resize(alignments.size());

    for (auto it = input.begin(); it != input.end(); ++it)
    {
      int startIndex = 0;
      int endIndex = -1;
      int width = 0;

      for (int i = 0; i < numberOfColumns; ++i)
      {
        if (i == numberOfColumns - 1)
        {
          endIndex = it->size();
        }
        else
        {
          endIndex = it->indexOf(seperator, startIndex);

          if (endIndex < 0)
          {
            return false;
          }
        }

        width = endIndex - startIndex;

        if (columnWidths[i] < width)
        {
          columnWidths[i] = width;
        }

        startIndex = endIndex + 1;
      }
    }

    for (auto it = input.begin(); it != input.end(); ++it)
    {
      int startIndex = 0;
      int endIndex = -1;
      int width = 0;
      int nSpacesToInsert = 0;

      for (int i = 0; i < numberOfColumns; ++i)
      {
        if (i == numberOfColumns - 1)
        {
          endIndex = it->size();
        }
        else
        {
          endIndex = it->indexOf(seperator, startIndex);

          if (endIndex < 0)
          {
            return false;
          }
        }

        width = endIndex - startIndex;

        nSpacesToInsert = columnWidths[i] - width;

        if (alignments[i] == '<')
        {
          if (i != numberOfColumns - 1)
          {
            for (int j = 0; j < nSpacesToInsert; ++j)
            {
              it->insert(endIndex, ' ');
            }
          }
        }
        else if (alignments[i] == '>')
        {
          for (int j = 0; j < nSpacesToInsert; ++j)
          {
            it->insert(startIndex, ' ');
          }
        }

        startIndex = endIndex + 1 + nSpacesToInsert;
      }
    }

    return true;
  }
}