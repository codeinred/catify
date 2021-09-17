# A simple project to prettify commit messages

Commit messages are good. They provide information about tons of things. But far
too many commit messages lack emojis! This is a critical problem, and one that I
 will not stand for.

Catify solves this issue. In order to use catify, build and itstall it:

```bash
./build.sh
./install.sh
```
This will place catify in `~/.local/git-hooks/prepare-commit-message`. Then,
whenever you'd like to use catify, simply add

```bash
git config core.hooksPath "$HOME/.local/git-hooks"
```
In whichever repository you'd like to catify!

You can also enable it globally by running:

```bash
git config --global core.hooksPath "$HOME/.local/git-hooks"
```
And you're done!

[Catify Example](/catify.png)
