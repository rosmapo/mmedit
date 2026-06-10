local L = {}

L.lexer = "matlab"

L.singleLineComment = "% "

L.extensions = {
	"m",
}

L.keywords = {
	[0] = "break case catch classdef continue else elseif end for function global if otherwise parfor persistent return switch try while",
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT"] = {
		id = 1,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMAND"] = {
		id = 2,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["NUMBER"] = {
		id = 3,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1F1F1F),
	},
	["INSTRUCTION WORD"] = {
		id = 4,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["STRING"] = {
		id = 5,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["OPERATOR"] = {
		id = 6,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["IDENTIFIER"] = {
		id = 7,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["DOUBLE QUOTE STRING"] = {
		id = 8,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
}
return L
