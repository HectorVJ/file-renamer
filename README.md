# file-renamer

Batch file rename tool supporting prefix/suffix addition, keyword replacement, sequential numbering, preview mode, and conflict detection.

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Usage

```
Usage: file-renamer [options]
Options:
  --help          Show this help message
  --input <path>  Specify input directory (required)
  --preview       Preview rename results without executing
  --execute       Execute actual rename operations
  --ext <ext>     Filter by extension (e.g., txt)
  --keyword <str> Filter filenames by keyword
  --prefix <str>  Add prefix to filenames
  --suffix <str>  Add suffix to filenames
  --replace <old> Replace keyword in filenames
  --with <new>    New keyword for replacement
  --number        Enable sequential numbering
  --start <n>     Starting number (default: 1)
  --width <n>     Number width with zero-padding (default: 3)
```

## Examples

Preview mode:
```
./file-renamer --input sample/demo_files --preview --prefix new_ --ext txt
```

Execute mode:
```
./file-renamer --input sample/demo_files --execute --prefix doc_ --number --start 1 --width 3
```

Replace keyword:
```
./file-renamer --input sample/demo_files --preview --replace old --with new
```

Filter by keyword:
```
./file-renamer --input sample/demo_files --preview --keyword demo --suffix _done
```
