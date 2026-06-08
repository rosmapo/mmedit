local L = {}

L.lexer = "ihex"

L.extensions = {
	"hex",
}

L.keywords = {
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["RECSTART"] = {
		id = 1,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
	},
	["RECTYPE"] = {
		id = 2,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
	},
	["RECTYPE_UNKNOWN"] = {
		id = 3,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 2,
	},
	["BYTECOUNT"] = {
		id = 4,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0xFFFFFF),
	},
	["BYTECOUNT_WRONG"] = {
		id = 5,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0x3D0000),
	},
	["NOADDRESS"] = {
		id = 6,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["DATAADDRESS"] = {
		id = 7,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0xFFFFFF),
	},
	["STARTADDRESS"] = {
		id = 9,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0xFFFFFF),
	},
	["ADDRESSFIELD_UNKNOWN"] = {
		id = 10,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 2,
	},
	["EXTENDEDADDRESS"] = {
		id = 11,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0xFFFFFF),
	},
	["DATA_ODD"] = {
		id = 12,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["DATA_EVEN"] = {
		id = 13,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["DATA_UNKNOWN"] = {
		id = 14,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 2,
	},
	["DATA_EMPTY"] = {
		id = 15,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["CHECKSUM"] = {
		id = 16,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["CHECKSUM_WRONG"] = {
		id = 17,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0x3D0000),
	},
	["GARBAGE"] = {
		id = 18,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 2,
	},
}
return L
