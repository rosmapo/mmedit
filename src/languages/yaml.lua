local L = {}

L.lexer = "yaml"

L.singleLineComment = "# "

L.extensions = {
	"yml",
	"yaml",
}

L.keywords = {
	[0] = "true false yes no",
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["IDENTIFIER"] = {
		id = 2,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["COMMENT"] = {
		id = 1,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["INSTRUCTION WORD"] = {
		id = 3,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["NUMBER"] = {
		id = 4,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
	},
	["REFERENCE"] = {
		id = 5,
		fgColor = rgb(0xFFE0A0),
		bgColor = rgb(0xFFFFFF),
	},
	["DOCUMENT"] = {
		id = 6,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
	},
	["TEXT"] = {
		id = 7,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["ERROR"] = {
		id = 8,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
	},
}
return L
