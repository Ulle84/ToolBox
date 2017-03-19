# Next steps

# Bugs
* "//" is detected as begin of comment -> CommentHandler and StringHandler must be one class where the signs are parsed one by one -> CommentAndStringExtractor

# ToDo
* ui -> m_ui?
* always break line after ' : ' ?`class COMMS_ZILO_API ZILO_BlockTransfer : public AccessObject_BlockTransfer,`
* remove unnecessary "QT_NAMESPACE::" stuff
* improve performance by saving last clean date/time and compare to last changed date/time - open issues: what if the file is run again, but with different settings? - idea: append int value to checksum
* simplify options - make all options parametrizable
* do line delimiter replacement smarter -> look at each line individually
* remove leading * in block comments - AStyle cleaning is not reliable enough -> own implementation in CommentHandler

# Ideas
* remove id's?
* Test mode -t creates Preview and opens BeyondCompare -> only for files
* Primitive Type Replacement map Bool -> bool
* long version of command line paramters -f --> --files -d --> --directories etc
* test-mode -> only show current and expected file content
* parameterfile which fills class options
* sort includes (in blocks and alphabetically)
  * std includes
  * Qt includes
  * own includes
* add linebreak before public: private: etc. (before clearing doubled whitespace)