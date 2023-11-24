# Standards for code documentation

The following are a simple set of _guidelines_ aimed at keeping documentation across the project more consistent:

- All documentation is mainly found in **_this folder_**. In-Code docs (i.e comments above functions explaining parameter conditions and return values) aren't _neccesary_, but they're _greatly appreciated_. We're not using GitHub wiki or other features for this projects (sadly, there's too much work to do already).
- Some basic conventions:
     - Use `ProperCamelCase` for doc file names
     - Use [square braces] for in-line comments (i.e things such as [TODO: update this line] or [WARNING: this may change at any moment]), and `====\n equal sign separators\n ====` for block comments
     - Markdown source formatting is irrelevant. Most IDEs auto-format markdown to their standar anyways
- Prioritize _high level explanations_ over implementation details. The main focus of these docs is not to understand _how the code works_, ti's to understand _how is it used_ and _how can I integrate it_ with my code.
- _Try to keep everything up to date_, especially changes that may impact other parts of the project (i.e interface changes, return value changes...)
- Try to keep a _simple folder structure_. Having 27 mostly empty subfolders only makes docs harder to browse and read. Same with a single folder with 100+ files. Try to keep a sensible root structure, with appropiate names, so that everything is easy to find. It'd be better if the root `docs/` directory only contains this file though.
- _Use markdown features_. Having to read through 200+ lines of just plain text is a pain. Use _font styling_ to emphasize **important parts**, and use titles and lists to give a friendlier structure to your docs.
- English is preferred for consistensy, but Spanish is acceptable [I will probably translate everything as soon as I can tho]
