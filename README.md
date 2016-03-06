# emojicode-packages
A handful of simple packages for [Emojicode](http://www.emojicode.org/).

```
📦 helloworld 🔴

🐇 🐼 🍇
  🐇 🐖 🏁 ➡️ 🚂 🍇

    😀 🍩 🌍 👋
    😀 🍩 🙋 👋 🔤Hannah🔤

    🍎 0
  🍉
🍉
```

```
$ emojicodec helloworld.emojic
$ emojicode helloworld.emojib
Hello World!
Hello Hannah!
```

## Package List
All commands are documented within their `.emojic` header files
- [helloworld](https://github.com/colinking/emojicode-packages/blob/master/src/helloworld/helloworld.emojic)
  - For a simple introduction to writing packages for Emojicode
- [commands](https://github.com/colinking/emojicode-packages/blob/master/src/commands/commands.emojic)
  - Run arbitrary system commands and have the output returned as a string

## Installation
To install these packages:

1. If you haven't already, [install Emojicode](http://www.emojicode.org/docs/guides/)

2. [Download](https://github.com/colinking/emojicode-packages/archive/master.zip) the master branch of this repo and unzip it.

3. Run `make`

## Write New Packages

To create a new package, named `example-package`:

1. Create a new `.emojic` header file and `.c` implementation file in `src/example-package/` named `example-package.emojic` and `example-package.c`, respectively

2. Fill out the `.emojic` and `.c` files by using the [helloworld](https://github.com/colinking/emojicode-packages/blob/master/src/helloworld/helloworld.emojic) package, [commands](https://github.com/colinking/emojicode-packages/blob/master/src/commands/commands.emojic) package or any of the [default Emojicode](https://github.com/emojicode/emojicode/tree/master/DefaultPackages) packages as references

3. Add your package to the `Makefile` by adding it to the `PACKAGES` variable: `PACKAGES = helloworld commands example-package`

4. Run `make`

5. Import your new package with `📦 example-package 🔴`
