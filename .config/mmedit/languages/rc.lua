local L = {}

L.lexer = "rc"

L.singleLineComment = "// "

L.extensions = {
	"rc",
}

L.keywords = {
	[0] = "ACCELERATORS ALT AUTO3STATE AUTOCHECKBOX AUTORADIOBUTTON BEGIN BITMAP BLOCK BUTTON CAPTION CHARACTERISTICS CHECKBOX CLASS COMBOBOX CONTROL CTEXT CURSOR DEFPUSHBUTTON DIALOG DIALOGEX DISCARDABLE EDITTEXT END EXSTYLE FONT GROUPBOX ICON LANGUAGE LISTBOX LTEXT MENU MENUEX MENUITEM MESSAGETABLE POPUP PUSHBUTTON RADIOBUTTON RCDATA RTEXT SCROLLBAR SEPARATOR SHIFT STATE3 STRINGTABLE STYLE TEXTINCLUDE VALUE VERSION VERSIONINFO VIRTKEY",
}

L.styles = {
	["PREPROCESSOR"] = {
		id = 9,
		fgColor = rgb(0xFFE0A0),
		bgColor = rgb(0x1F1F1F),
	},
	["DEFAULT"] = {
		id = 11,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["INSTRUCTION WORD"] = {
		id = 5,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["TYPE WORD"] = {
		id = 16,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["NUMBER"] = {
		id = 4,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1F1F1F),
	},
	["STRING"] = {
		id = 6,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["CHARACTER"] = {
		id = 7,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["OPERATOR"] = {
		id = 10,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["VERBATIM"] = {
		id = 13,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["REGEX"] = {
		id = 14,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["COMMENT"] = {
		id = 1,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT LINE"] = {
		id = 2,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT DOC"] = {
		id = 3,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT LINE DOC"] = {
		id = 15,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT DOC KEYWORD"] = {
		id = 17,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["COMMENT DOC KEYWORD ERROR"] = {
		id = 18,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
	["PREPROCESSOR COMMENT"] = {
		id = 23,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["PREPROCESSOR COMMENT DOC"] = {
		id = 24,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
}
return L
