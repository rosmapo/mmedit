local L = {}

L.lexer = "smalltalk"

L.extensions = {
	"st",
}

L.keywords = {
	[0] = "ifTrue: ifFalse: whileTrue: whileFalse: ifNil: ifNotNil: whileTrue whileFalse repeat isNil notNil",
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["STRING"] = {
		id = 1,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["NUMBER"] = {
		id = 2,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMENT"] = {
		id = 3,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["SYMBOL"] = {
		id = 4,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["BINARY"] = {
		id = 5,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
	},
	["BOOL"] = {
		id = 6,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["SELF"] = {
		id = 7,
		fgColor = rgb(0x9CDCFE),
		bgColor = rgb(0x1E1E1E),
		fontStyle = 1,
	},
	["SUPER"] = {
		id = 8,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0x1E1E1E),
		fontStyle = 1,
	},
	["NIL"] = {
		id = 9,
		fgColor = rgb(0x9CDCFE),
		bgColor = rgb(0xFFFFFF),
	},
	["GLOBAL"] = {
		id = 10,
		fgColor = rgb(0xFFA0A0),
		bgColor = rgb(0xFFFFFF),
	},
	["RETURN"] = {
		id = 11,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["SPECIAL"] = {
		id = 12,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0xFFFFFF),
	},
	["KWS END"] = {
		id = 13,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0xFFFFFF),
	},
	["ASSIGN"] = {
		id = 14,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
	},
	["CHARACTER"] = {
		id = 15,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["SPECIAL SELECTOR"] = {
		id = 16,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
}
return L
