# Required lib files

- libboost_chrono_vc120-mt-gd-1_57.lib
- libboost_date_time_vc120-mt-gd-1_57.lib
- libboost_regex_vc120-mt-gd-1_57.lib
- libboost_system_vc120-mt-gd-1_57.lib
- libboost_thread_vc120-mt-gd-1_57.lib

These are all part of the [Boost C++ Libraries](http://www.boost.org), and are
created when you build Boost on your machine. You can download the library at
[http://www.boost.org/users/history/version_1_57_0.html](http://www.boost.org/users/history/version_1_57_0.html),
and instructions to build are available at [http://www.boost.org/build/doc/html/bbv2/installation.html](http://www.boost.org/build/doc/html/bbv2/installation.html).

Once the build is complete (this can take some time), find the appropriate lib
files, located in the build output directory (by default `/bin.v2`, relative to
the wherever you extracted the Boost library).
