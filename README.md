Refer to https://gtlang.com for details.

# Introduction
Green Tea is aimed for people who are new to programming, just like Sketch. It is a simple language that purpose is removing all the things you should remember and let you deploy your idea in Zen mode. "Your ideas matter, not the syntax".

+ Simple and easy to learn, even for people haven’t know anything about programming
+ Easy to switch from other languages
+ Could be used to syntactically convert a source code of a language to another.
+ Use your native language to code. Why do you have to learn English fore code?

Green Tea is inspired by PHP, and is a script/compiled language, functional/object-oriented language.

Parts of this document is copied from the PHP manual.

# Compiling

```bash
cd gtlang
make clean
make all
```
# Prerequisites

Green Tea is made for newcomers. No prerequisites here.

# Installation

## Windows

Not suported yet

## Linux

Generally, you just need to download the binary, put it somewhere, chmox +x it, then add it parent folder to PATH environment variable.

### Debian

### Centos

## MacOS

Not suported

# Usage
## Interprept

    gtlang <sourcefile>

Ex: 

    gtlang hello_world.gtc

## Compile:

    gtcompiler <sourcefile> <output file>

Ex: 

    gtcompiler hello_world.gtc hello_world

# Language file

Green Tea is the multi-language programming language

To use another language, use use_language_file keyword

The variables’ name, functions’ name, classes’ name, keywords could be translated, but hard-codded strings could not.


Ex:

In ru.gtlang, we could define:

    if : если

    for : для

    echo : эхо

    number : номер

    // (could add more here)

in the source file, use

    use_language_file ru.gtlang

now you could code:

    если $номер=0

        @эхо “\$номер ноль”
