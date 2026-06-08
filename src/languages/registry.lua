local L = {}

L.lexer = "registry"

L.singleLineComment = "; "

L.extensions = {
	"reg",
}

L.keywords = {
}

L.styles = {
	["DEFAULT STYLE"] = {
		id = 32,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMENT"] = {
		id = 1,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["VALUE NAME"] = {
		id = 2,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
	},
	["STRING"] = {
		id = 3,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["HEX DIGIT"] = {
		id = 4,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
	},
	["VALUE TYPE"] = {
		id = 5,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["ADDED KEY"] = {
		id = 6,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["REMOVED KEY"] = {
		id = 7,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
	},
	["ESCAPED CHARACTERS IN STRINGS"] = {
		id = 8,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["GUID IN KEY PATH"] = {
		id = 9,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0xFFFFFF),
	},
	["GUID IN STRING"] = {
		id = 10,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0xFFFFFF),
	},
	["PARAMETER"] = {
		id = 11,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0xFFFFFF),
	},
	["OPERATORS"] = {
		id = 12,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
}
return L
