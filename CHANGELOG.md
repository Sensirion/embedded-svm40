# Changelog

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.2.3] - 2021-01-06

 * `[changed]` Print warning if the firmware version is older than 2.2 in the examples

## [0.2.2] - 2020-12-15

 * `[changed]` Updated embedded-common to 0.1.0 to improve compatibility when
               using multiple embedded drivers

## [0.2.1] - 2020-11-05

 * `[added]` Arduino Release zip and Documentation on how to run the included
             example usage on an Arduino platform.

## [0.2.0] - 2020-11-02

 * `[added]`   Reset Device function
 * `[added]`   Get serial command to SVM40 driver
 * `[added]`   Read Measured Values As Integers With Raw Parameters command to
               SVM40 driver
 * `[changed]` Add delays to all functions to match the hardware specification
 * `[changed]` Only include needed files from embedded-common in release zip

## [0.1.0] - 2020-09-01

 * First release with support for the basic commands

[Unreleased]: https://github.com/Sensirion/embedded-svm40/compare/0.2.3...master
[0.2.3]: https://github.com/Sensirion/embedded-svm40/compare/0.2.2...0.2.3
[0.2.2]: https://github.com/Sensirion/embedded-svm40/compare/0.2.1...0.2.2
[0.2.1]: https://github.com/Sensirion/embedded-svm40/compare/0.2.0...0.2.1
[0.2.0]: https://github.com/Sensirion/embedded-svm40/compare/0.1.0...0.2.0
[0.1.0]: https://github.com/Sensirion/embedded-svm40/releases/tag/0.1.0
