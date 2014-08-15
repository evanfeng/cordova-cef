Humble Logging Library (C++)
============================
Lightweight C++ Logging Library


Features
========
- Thread-Safe logging.
- Multi-Process-Safe logging (based on Appender).
- Custom logger name pattern.
- Configurable LogLevel by config file.
- Changable LogLevel and Appenders during runtime.
- Multiple Appenders for each Logger.
- Simple API to implement custom Appenders.
- Custom format for log messages (Formatter).


Built-in Appenders
------------------
- **NullAppender**
  Doesn't log anything. It's used for performance testing.
- **ConsoleAppender**
  Logs to STDOUT console and optionally to Visual Studio's Application Output Window.
- **FileAppender**
  Logs to a file. No further options.
- **RollingFileAppender**
  Logs to a file. Configurable roll-count and file size.


Built-in Formatters
-------------------
- **SimpleFormatter**
  The default Formatter, which includes most important information in a predefined layout.
- **PatternFormatter**
  Provides placeholders to define a custom log messages format (e.g. ``[%date] [%lls] [line=%line] [file=%filename] %m\n``)


Dependencies
============
Except the STL (Standard Template Library), which should be on nearly every system,
the project doesn't require third-party libraries.

**Linux**
- ``std::mutex``
- ``pthread`` for ``./examples/mtperformance``


How To Build
============
Type on your console
::

  cd $PROJECT_DIRECTORY
  mkdir build
  cd build
  cmake -DCMAKE_INSTALL_PREFIX:PATH=/tmp/humblelogging ..
  
After you ran these commands you should have a ``Makefile`` or Visual Studio solution ``*.sln`` to build the library.
The ``install`` target will copy all public headers, libraries and cmake scripts into the ``CMAKE_INSTALL_PREFIX`` directory.


Build Options
-------------
cmake -DBuildShared=OFF
  Builds the library as static or shared library.
  ``default=ON``
  
cmake -DBuildExamples=OFF
  Builds all sub projects in the ``./examples/`` folder.
  ``default=ON``


Examples
========
See the ``./examples/basic/`` and ``./examples/configured`` folders for an short introduction.


Example configuration file
--------------------------
The example configuration shows, that it is not required to rely on a specific pattern of Logger names.
The framework is based on simple strings and prefix searches. If it is required to specify a log-level recursive
the wildcard (*) have to be used.
::

  # Sets the default log-level to OFF.
  logger.level(*)=off
  
  # Specify a specific log-level for a few loggers.
  logger.level(core*)=fatal
  logger.level(core.network*)=error
  logger.level(core.network.tcp*)=debug
  
  # Some more loggers with different names.
  logger.level(Core*)=fatal
  logger.level(CoreNetwork*)=error
  logger.level(Audio*)=warn
  logger.level(Video*)=warn
  logger.level(VideoCapture*)=off


Build Compatibility
-------------------
The project build has been tested in the following environments.

- Windows 8.1 Update 1 Visual Studio 2008 (32 & 64 bit)
- Windows 8.1 Update 1 Visual Studio 2010 (32 & 64 bit)
- Windows 8.1 Update 1 Visual Studio 2012 (32 & 64 bit)
- Ubuntu 14.04 GCC 4.8 (32 & 64 bit)


Performance tests
=================
Feel free to contribute your tests (only release builds).
::
  # Windows 8.1 Update 1 32 bit / VC 2012 / Core i7 3770K @ 3.50 GHz
  # CMD: mtperformance_example.exe 4 20000000 null
  # Tester: mfreiholz
  Events: 80000000
  Threads: 4
  Duration: 12468 ms / 12.468000 s
  Throughput: 6416426.050690 events/second
