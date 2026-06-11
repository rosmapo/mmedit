local L = {}

L.lexer = "oscript"

L.singleLineComment = "// "

L.extensions = {
	"osx",
}

L.keywords = {
	[0] = "break breakif by case continue continueif default downto else elseif end for goto if in repeat switch to until while function return void dll inbyref inout linked nodebug super this xcmd xfcn",
	[1] = "false true undefined booleantype bytestype datatype dynamictype errortype externtype integertype listtype longtype objecttype objreftype pointtype realtype scripttype stringtype undefinedtype voidtype",
	[2] = "and eq ge gt le lt ne not or xor",
	[3] = "assoc boolean bytes date dynamic error extern file integer list long object point real recarray record script string cachetree capiconnect capierr capilog capilogin compiler dapisession dapinode dapiversion dapistream filecopy fileprefs frame javaobject mailmessage pop3session smtpsession ssloptions patfind patchange regex socket sqlconnection sqlcursor uapisession uapiuser wapisession wapimap wapimaptask wapiwork wapisubwork domattr domcdatasection domcharacterdata domcomment domdocument domdocumentfragment domdocumenttype domelement domentity domentityreference domimplementation domnamednodemap domnode domnodelist domnotation domparser domprocessinginstruction domtext saxparser xslprocessor",
	[4] = "datatypename echo echodebug echoerror echoinfo echostamp echowarn getfeatures isdefined iserror isfeature isinvokable isnoterror isnotset isobject isset isundefined length nparameters parameters pointh pointv type",
	[5] = "cachetree capiconnect capierr capilog capilogin compiler dapisession dapinode dapiversion dapistream filecopy fileprefs frame javaobject mailmessage pop3session smtpsession ssloptions patfind patchange regex socket sqlconnection sqlcursor uapisession uapiuser wapisession wapimap wapimaptask wapiwork wapisubwork domattr domcdatasection domcharacterdata domcomment domdocument domdocumentfragment domdocumenttype domelement domentity domentityreference domimplementation domnamednodemap domnode domnodelist domnotation domparser domprocessinginstruction domtext saxparser xslprocessor",
}

L.styles = {
	["DEFAULT TEXT STYLE"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["SINGLE-LINE COMMENT"] = {
		id = 1,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["MULTI-LINE COMMENT"] = {
		id = 2,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["#IFDEF DOC AND #ENDIF"] = {
		id = 3,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["PREPROCESSOR DIRECTIVE"] = {
		id = 4,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0x1F1F1F),
	},
	["NUMBER"] = {
		id = 5,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
	["STRING SINGLE QUOTES"] = {
		id = 6,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["STRING DOUBLE QUOTES"] = {
		id = 7,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["CONSTANT LITERAL"] = {
		id = 8,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1F1F1F),
	},
	["IDENTIFIER"] = {
		id = 9,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["SERVER-GLOBAL VARIABLE (PREFIXED BY $)"] = {
		id = 10,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["LANGUAGE NATIVE KEYWORD OR RESERVED WORD"] = {
		id = 11,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["OPERATOR; EITHER SYMBOLIC OR LITERAL"] = {
		id = 12,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["LABEL TO JUMP TO WITH THE GOTO STATEMENT"] = {
		id = 13,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["TYPE"] = {
		id = 14,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
	},
	["FUNCTION"] = {
		id = 15,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
	},
	["STATIC BUILT-IN OBJECT"] = {
		id = 16,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
	["OBJECT PROPERTY"] = {
		id = 17,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["OBJECT METHOD"] = {
		id = 18,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
}
return L
