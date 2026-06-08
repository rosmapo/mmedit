local L = {}

L.lexer = "json"

L.first_line = {
	"^{[\r\n]",
}

L.extensions = {
	"json",
}

L.properties = {
	["lexer.json.escape.sequence"] = "1",
	["lexer.json.allow.comments"] = "1",
}

L.keywords = {
	[0] = "false null true",
	[1] = "@id @context @type @value @language @container @list @set @reverse @index @base @vocab @graph",
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["NUMBER"] = {
		id = 1,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
	},
	["STRING"] = {
		id = 2,
		fgColor = rgb(0xFFA0A0),
		bgColor = rgb(0xFFFFFF),
	},
	["STRINGEOL"] = {
		id = 3,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["PROPERTYNAME"] = {
		id = 4,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["ESCAPESEQUENCE"] = {
		id = 5,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["LINECOMMENT"] = {
		id = 6,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["BLOCKCOMMENT"] = {
		id = 7,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["OPERATOR"] = {
		id = 8,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["URI"] = {
		id = 9,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
	},
	["COMPACTIRI"] = {
		id = 10,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["KEYWORD"] = {
		id = 11,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["LDKEYWORD"] = {
		id = 12,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
	},
	["ERROR"] = {
		id = 13,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
}
return L
