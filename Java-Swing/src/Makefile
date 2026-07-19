JAVAC = javac
JAVA = java

SOURCES = Main.java MainFrame.java Client.java
MAIN_CLASS = Main

all: compile

compile:
	$(JAVAC) $(SOURCES)

run: compile
	$(JAVA) $(MAIN_CLASS)

clean:
	rm -f *.class
