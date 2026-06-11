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
		bgColor = rgb(0x1F1F1F),
	},
	["STRING"] = {
		id = 1,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["NUMBER"] = {
		id = 2,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT"] = {
		id = 3,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["SYMBOL"] = {
		id = 4,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["BINARY"] = {
		id = 5,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
	},
	["BOOL"] = {
		id = 6,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
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
		bgColor = rgb(0x1F1F1F),
	},
	["GLOBAL"] = {
		id = 10,
		fgColor = rgb(0xFFA0A0),
		bgColor = rgb(0x1F1F1F),
	},
	["RETURN"] = {
		id = 11,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["SPECIAL"] = {
		id = 12,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0x1F1F1F),
	},
	["KWS END"] = {
		id = 13,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0x1F1F1F),
	},
	["ASSIGN"] = {
		id = 14,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1F1F1F),
	},
	["CHARACTER"] = {
		id = 15,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["SPECIAL SELECTOR"] = {
		id = 16,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
}
return L
