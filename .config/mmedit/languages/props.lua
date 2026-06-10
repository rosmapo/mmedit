local L = {}

L.lexer = "props"

L.singleLineComment = "# "

L.extensions = {
	"properties",
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
	["SECTION"] = {
		id = 2,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1E1E1E),
		fontStyle = 1,
	},
	["ASSIGNMENT"] = {
		id = 3,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["DEFVAL"] = {
		id = 4,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1F1F1F),
	},
	["KEY"] = {
		id = 5,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 2,
	},
}
return L
