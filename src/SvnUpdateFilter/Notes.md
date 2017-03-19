# Bugs

# ToDo

# Ideas
* do update via QProcess (svn update) - take std-output and analyze directly (no copy and paste required)
* lower textfield -> replace by list of clickable items -> double click on file shows diff with previous version

# General Description
Every time a SVN update is called a lot of messages are written.
It is hard to see the real changes to files.
With SvnUpdateFilter you can filter the relevant information.
Just copy the output from the TortoiseSVN-Update window and paste it into the upper textfield.
In the lower textfild the relevant messages are shown.

Created by Ulrich Belitz.