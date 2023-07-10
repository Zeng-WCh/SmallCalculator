CXX=g++
CXXFLAGS=-O2 -g
TARGET=calculator
SODIR=./lib
SRCDIR=./src
SOFLAGS=-shared -fPIC
INCLUDEDIR=./include

all: driver

ast: ${SRCDIR}/ast.cpp
	@mkdir -p ${SODIR}
	${CXX} -I${INCLUDEDIR} ${CXXFLAGS} ${SRCDIR}/ast.cpp ${SOFLAGS} -o ${SODIR}/libast.so -L${SODIR} -llexer

lexer: ${SRCDIR}/lexer.cpp
	@mkdir -p ${SODIR}
	${CXX} -I${INCLUDEDIR} ${CXXFLAGS} ${SRCDIR}/lexer.cpp ${SOFLAGS} -o ${SODIR}/liblexer.so

parser: ${SRCDIR}/parser.cpp
	@mkdir -p ${SODIR}
	${CXX} -I${INCLUDEDIR} ${CXXFLAGS} ${SRCDIR}/parser.cpp ${SOFLAGS} -o ${SODIR}/libparser.so -L${SODIR} -llexer

driver: lexer ast parser ${SRCDIR}/driver.cpp
	${CXX} -I${INCLUDEDIR} ${CXXFLAGS} ${SRCDIR}/driver.cpp -L${SODIR} -llexer -lparser -last -o ${TARGET}