# skred

A utility for mass deletion of huge numbers of files. Was up to 8% faster than rm under certain circumstances in testing. That said, I would just use rm. rm is surely far better written and tested.

### Usage

Will recursively delete a directory and all files and directories under it. Does not follow symlinks.
```bash
skred /path/to/target/directory/
```

Will create 2000 dirs with 2000 files each at the cwd (for testing purposes).
```bash
create
```
