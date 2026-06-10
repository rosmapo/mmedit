local L = {}

L.lexer = "tehex"

L.extensions = {
	"tek",
}

L.keywords = {
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["RECSTART"] = {
		id = 1,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1F1F1F),
	},
	["RECTYPE"] = {
		id = 2,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1F1F1F),
	},
	["RECTYPE_UNKNOWN"] = {
		id = 3,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 2,
	},
	["BYTECOUNT"] = {
		id = 4,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0x1F1F1F),
	},
	["BYTECOUNT_WRONG"] = {
		id = 5,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0x3D0000),
	},
	["DATAADDRESS"] = {
		id = 7,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0x1F1F1F),
	},
	["STARTADDRESS"] = {
		id = 9,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0x1F1F1F),
	},
	["ADDRESSFIELD_UNKNOWN"] = {
		id = 10,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 2,
	},
	["DATA_ODD"] = {
		id = 12,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["DATA_EVEN"] = {
		id = 13,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["CHECKSUM"] = {
		id = 16,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["CHECKSUM_WRONG"] = {
		id = 17,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0x3D0000),
	},
	["GARBAGE"] = {
		id = 18,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 2,
	},
}
return L
