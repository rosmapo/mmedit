local L = {}

L.lexer = "asp"

L.singleLineComment = "' "

L.extensions = {
	"asp",
}

L.keywords = {
	[0] = "addhandler addressof andalso alias and ansi as assembly attribute auto begin boolean byref byte byval call case catch cbool cbyte cchar cdate cdec cdbl char cint class clng cobj compare const continue cshort csng cstr ctype currency date decimal declare default delegate dim do double each else elseif end enum erase error event exit explicit false finally for friend function get gettype global gosub goto handles if implement implements imports in inherits integer interface is let lib like load long loop lset me mid mod module mustinherit mustoverride mybase myclass namespace new next not nothing notinheritable notoverridable object on option optional or orelse overloads overridable overrides paramarray preserve private property protected public raiseevent readonly redim rem removehandler rset resume return select set shadows shared short single static step stop string structure sub synclock then throw to true try type typeof unload unicode until variant wend when while with withevents writeonly xor",
}

L.styles = {
	["DEFAULT"] = {
		id = 81,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1E2D2D),
	},
	["COMMENTLINE"] = {
		id = 82,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1E2D2D),
	},
	["NUMBER"] = {
		id = 83,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1E2D2D),
	},
	["WORD"] = {
		id = 84,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1E2D2D),
		fontStyle = 1,
	},
	["STRING"] = {
		id = 85,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1E2D2D),
	},
	["IDENTIFIER"] = {
		id = 86,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1E2D2D),
	},
	["ASPSYMBOL"] = {
		id = 15,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x2D2D00),
		fontStyle = 1,
	},
	["SCRIPTTYPE"] = {
		id = 16,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x2D2000),
	},
}
return L
