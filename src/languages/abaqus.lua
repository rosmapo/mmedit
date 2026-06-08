local L = {}

L.lexer = "abaqus"

L.singleLineComment = ""

L.extensions = {
	"inp",
}

L.keywords = {
}

L.styles = {
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
	["NUMBER"] = {
		id = 3,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
	},
	["STRING"] = {
		id = 4,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
	},
	["OPERATOR"] = {
		id = 5,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
	},
	["PROCESSORS"] = {
		id = 7,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["STARCOMMAND"] = {
		id = 10,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
	},
	["ARGUMENT"] = {
		id = 11,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
}
return L
