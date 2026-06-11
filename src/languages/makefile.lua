local L = {}

L.lexer = "makefile"

L.singleLineComment = "# "

L.extensions = {
	"mak",
	"mk",
}

L.keywords = {
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
	["PREPROCESSOR"] = {
		id = 2,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x3C3C3C),
		fontStyle = 1,
	},
	["IDENTIFIER"] = {
		id = 3,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
	},
	["OPERATOR"] = {
		id = 4,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["TARGET"] = {
		id = 5,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1F1F1F),
	},
	["IDEOL"] = {
		id = 9,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 2,
	},
}
return L
