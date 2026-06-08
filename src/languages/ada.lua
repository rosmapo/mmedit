local L = {}

L.lexer = "ada"

L.singleLineComment = "-- "

L.extensions = {
	"ada",
	"ads",
	"adb",
}

L.keywords = {
	[0] = "abort abs abstract accept access aliased all and array at begin body case constant declare delay delta digits do else elsif end entry exception exit for function generic goto if in interface is limited loop mod new not null of or others out overriding package pragma private procedure protected raise range record rem renames requeue return reverse select separate some subtype synchronized tagged task terminate then type until use when while with xor",
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["INSTRUCTION WORD"] = {
		id = 1,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["IDENTIFIER"] = {
		id = 2,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["NUMBER"] = {
		id = 3,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
	},
	["DELIMITER"] = {
		id = 4,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["CHARACTER"] = {
		id = 5,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["STRING"] = {
		id = 7,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["LABEL"] = {
		id = 9,
		fgColor = rgb(0xFFE0A0),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["COMMENT LINE"] = {
		id = 10,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["ILLEGAL"] = {
		id = 11,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
	},
}
return L
