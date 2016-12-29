cd $(dirname $0)

unzip topcoder-moj-4.18.zip
patch topcoder-moj-4.18/src/moj/CPPHarnessGenerator.java < CPPHarnessGenerator.patch

cd topcoder-moj-4.18
mkdir bin
winpty javac -classpath deps/ContestApplet.jar -sourcepath src -d bin src/moj/moj.java
winpty jar cvf deploy/moj.jar -C bin moj

cp -a deps/CodeProcessor.jar deps/FileEdit.jar deploy/moj.jar ..

cd ..
rm -rf topcoder-moj-4.18
