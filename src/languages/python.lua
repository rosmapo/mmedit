local L = {}

L.lexer = "python"

L.singleLineComment = "# "

L.tabSize = 4

L.tabSettings = "spaces"

L.first_line = {
	"^#!.*python"
}

L.extensions = {
	"py",
	"pyw",
}

L.properties = {
    ["lexer.python.keywords2.no.sub.identifiers"] = "1",
    ["lexer.python.decorator.attributes"] = "1"
}

L.keywords = {
	[0] = "and as assert async await break case class continue def del elif else except finally for from global if import in is lambda match nonlocal not or pass raise return try while with yield self",
	[1] = "ArithmeticError AssertionError AttributeError BaseException BlockingIOError BrokenPipeError BufferError BytesWarning ChildProcessError ConnectionAbortedError ConnectionError ConnectionRefusedError ConnectionResetError DeprecationWarning EOFError Ellipsis EnvironmentError Exception False FileExistsError FileNotFoundError FloatingPointError FutureWarning GeneratorExit IOError ImportError ImportWarning IndentationError IndexError InterruptedError IsADirectoryError KeyError KeyboardInterrupt LookupError MemoryError ModuleNotFoundError NameError None NotADirectoryError NotImplemented NotImplementedError OSError OverflowError PendingDeprecationWarning PermissionError ProcessLookupError RecursionError ReferenceError ResourceWarning RuntimeError RuntimeWarning StopAsyncIteration StopIteration SyntaxError SyntaxWarning SystemError SystemExit TabError TimeoutError True TypeError UnboundLocalError UnicodeDecodeError UnicodeEncodeError UnicodeError UnicodeTranslateError UnicodeWarning UserWarning ValueError Warning WindowsError ZeroDivisionError abs all any ascii bin bool breakpoint bytearray bytes callable chr classmethod compile complex copyright credits delattr dict dir divmod enumerate eval exec exit filter float format frozenset getattr globals hasattr hash help hex id input int isinstance issubclass iter len license list locals map max memoryview min next object oct open ord pow print property quit range repr reversed round set setattr slice sorted staticmethod str sum super tuple type vars zip",
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4), -- Hlavná svetlosivá
		bgColor = rgb(0x1E1E1E),
	},
	["COMMENTLINE"] = {
		id = 1,
		fgColor = rgb(0x6A9955), -- Klasické zelené komentáre (#)
		bgColor = rgb(0x1E1E1E),
	},
	["NUMBER"] = {
		id = 2,
		fgColor = rgb(0xB5CEA8), -- Svetlozelená pre čísla
		bgColor = rgb(0x1E1E1E),
	},
	["STRING"] = {
		id = 3,
		fgColor = rgb(0xCE9178), -- Tradičná oranžovo-hnedá pre stringy
		bgColor = rgb(0x1E1E1E),
	},
	["CHARACTER"] = {
		id = 4,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1E1E1E),
	},
	["KEYWORDS"] = {
		id = 5,
		fgColor = rgb(0x569CD6), -- Modrá pre riadiace kľúčové slová (if, for, return...)
		bgColor = rgb(0x1E1E1E),
		fontStyle = 1,
	},
	["BUILTINS"] = {
		id = 14,
		fgColor = rgb(0x4EC9B0), -- Tyrkysová pre zabudované Python funkcie/výnimky (print, len, ValueError...)
		bgColor = rgb(0x1E1E1E),
		fontStyle = 1,
	},
	["TRIPLE"] = {
		id = 6,
		fgColor = rgb(0xCE9178), -- Viacriadkové stringy (Docstringy)
		bgColor = rgb(0x1E1E1E),
	},
	["TRIPLEDOUBLE"] = {
		id = 7,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1E1E1E),
	},
	["CLASSNAME"] = {
		id = 8,
		fgColor = rgb(0x4EC9B0), -- Tyrkysová pre názvy tried za kľúčovým slovom class
		bgColor = rgb(0x1E1E1E),
		fontStyle = 1,
	},
	["DEFNAME"] = {
		id = 9,
		fgColor = rgb(0xDCDCAA), -- Žltá pre názvy funkcií pri definícii (def funkcia:)
		bgColor = rgb(0x1E1E1E),
	},
	["OPERATOR"] = {
		id = 10,
		fgColor = rgb(0xD4D4D4), -- Štandardná sivobiela pre operátory (+, ==, *, ...)
		bgColor = rgb(0x1E1E1E),
		fontStyle = 1,
	},
	["IDENTIFIER"] = {
		id = 11,
		fgColor = rgb(0x9CDCFE), -- Svetlomodrá pre premenné a argumenty
		bgColor = rgb(0x1E1E1E),
	},
	["COMMENTBLOCK"] = {
		id = 12,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1E1E1E),
	},
	["DECORATOR"] = {
		id = 15,
		fgColor = rgb(0xDCDCAA), -- Žltkastá pre dekorátory (@staticmethod...)
		bgColor = rgb(0x1E1E1E),
		fontStyle = 2,
	},
	["F STRING"] = {
		id = 16,
		fgColor = rgb(0xCE9178), -- F-stringy vo VS Code majú rovnakú farbu ako bežné stringy
		bgColor = rgb(0x1E1E1E),
	},
	["F CHARACTER"] = {
		id = 17,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1E1E1E),
	},
	["F TRIPLE"] = {
		id = 18,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1E1E1E),
	},
	["F TRIPLEDOUBLE"] = {
		id = 19,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1E1E1E),
	},
}
return L