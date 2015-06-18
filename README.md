# Stibbons

![Stibbons logo](https://raw.githubusercontent.com/Ynigvi/stibbons/master/data/images/stibbons-full.png)

The Stibbons project's development began within the context of the AIGLE (Software and Web Architecture and Engineering) master of Faculty of Science, University of Montpellier.

The project provide a new multi-agent programming language called Stibbons. It is built in C++11 and its applications use the Qt framework.

Two applications are proposed to answer to different cases:
- a GUI based application alowing to develop and run Stibbons programs,
- a CLI based application used to run Stibbons programs without the need of a windowing system and to regularly export the generated model.

## Dependencies

- C++11
- Qt 5.0
- Flex
- Bison
- Json Spirit 4.0.4 (requires Boost)
- CppUnit

## Compile

### All

`make` or `make all`

### Clean

`make clean`

### Applications

#### GUI application

`make stibbons`

#### CLI application

`make stibbons-cli`

#### Unit tests

`make test`

### Documentation (french)

`make doc`

#### Report

`make report`

#### Project management report

`make project`

#### Keynote

`make keynote`

