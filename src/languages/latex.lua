local L = {}

L.lexer = "latex"

L.singleLineComment = "% "

L.extensions = {
	"tex",
	"sty",
}

L.keywords = {
}

L.styles = {
	["WHITE SPACE"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMAND"] = {
		id = 1,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["TAG OPENING"] = {
		id = 2,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["MATH INLINE"] = {
		id = 3,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMENT"] = {
		id = 4,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["TAG CLOSING"] = {
		id = 5,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["MATH BLOCK"] = {
		id = 6,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMENT BLOCK"] = {
		id = 7,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["VERBATIM SEGMENT"] = {
		id = 8,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["SHORT COMMAND"] = {
		id = 9,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["SPECIAL CHAR"] = {
		id = 10,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMAND OPTIONAL ARGUMENT"] = {
		id = 11,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0xFFFFFF),
	},
	["SYNTAX ERROR"] = {
		id = 12,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x3D0000),
	},
}
return L
