local L = {}

L.lexer = "cpp"

L.singleLineComment = "// "

L.extensions = {
    "js",
    "mjs",
    "cjs",
    "jsm",
    "jsx",
    "ts",
    "tsx",
}

L.properties = {
    ["lexer.cpp.backquoted.strings"] = "1",
}

L.keywords = {
    [0] = "abstract async await boolean break byte case catch char class const continue debugger default delete do double else enum export extends final finally float for function goto if implements import in instanceof int interface let long native new null of package private protected public return short static super switch synchronized this throw throws transient try typeof var void volatile while with true false prototype yield from as",
    [1] = "Array Date eval hasOwnProperty Infinity isFinite isNaN isPrototypeOf Math NaN Number Object prototype String toString undefined valueOf",
    [3] = "alert all anchor anchors area assign blur button checkbox clearInterval clearTimeout clientInformation close closed confirm constructor crypto decodeURI decodeURIComponent defaultStatus document element elements embed embeds encodeURI encodeURIComponent escape event fileUpload focus form forms frame innerHeight innerWidth layer layers link location mimeTypes navigate navigator frames frameRate hidden history image images offscreenBuffering onblur onclick onerror onfocus onkeydown onkeypress onkeyup onmouseover onload onmouseup onmousedown onsubmit open opener option outerHeight outerWidth packages pageXOffset pageYOffset parent parseFloat parseInt password pkcs11 plugin prompt propertyIsEnum radio reset screenX screenY scroll secure select self setInterval setTimeout status submit taint text textarea top unescape untaint window",
}

L.styles = {
    ["DEFAULT"] = {
        id = 11,
        fgColor = rgb(0x9CDCFE), -- Svetlomodrá pre premenné / identifikátory
        bgColor = rgb(0x1E1E1E), -- VS Code tmavé pozadie
    },
    ["INSTRUCTION WORD"] = {
        id = 5,
        fgColor = rgb(0x569CD6), -- Klasická modrá pre kľúčové slová (if, function, return...)
        bgColor = rgb(0x1E1E1E),
        fontStyle = 1,
    },
    ["TYPE WORD"] = {
        id = 16,
        fgColor = rgb(0x4EC9B0), -- Tyrkysová pre typy a zabudované objekty (Object, Array...)
        bgColor = rgb(0x1E1E1E),
    },
    ["WINDOW INSTRUCTION"] = {
        id = 19,
        fgColor = rgb(0xDCDCAA), -- Žltkastá pre globálne funkcie a metódy (window, alert...)
        bgColor = rgb(0x1E1E1E),
        fontStyle = 1,
    },
    ["NUMBER"] = {
        id = 4,
        fgColor = rgb(0xB5CEA8), -- Svetlozelená pre čísla
        bgColor = rgb(0x1E1E1E),
    },
    ["STRING"] = {
        id = 6,
        fgColor = rgb(0xCE9178), -- Oranžovo-hnedá pre stringy
        bgColor = rgb(0x1E1E1E),
    },
    ["STRINGRAW"] = {
        id = 20,
        fgColor = rgb(0xCE9178), -- Template literály (backticks) vo VS Code
        bgColor = rgb(0x2D2D2D), -- Mierne odlišné pozadie pre raw stringy
    },
    ["CHARACTER"] = {
        id = 7,
        fgColor = rgb(0xCE9178),
        bgColor = rgb(0x1E1E1E),
    },
    ["OPERATOR"] = {
        id = 10,
        fgColor = rgb(0xD4D4D4), -- Svetlosivá / biela pre operátory (+, -, =, ...)
        bgColor = rgb(0x1E1E1E),
        fontStyle = 1,
    },
    ["VERBATIM"] = {
        id = 13,
        fgColor = rgb(0x9CDCFE),
        bgColor = rgb(0x1E1E1E),
    },
    ["REGEX"] = {
        id = 14,
        fgColor = rgb(0xD16969), -- Červenkastá pre regulárne výrazy
        bgColor = rgb(0x1E1E1E),
        fontStyle = 1,
    },
    ["COMMENT"] = {
        id = 1,
        fgColor = rgb(0x6A9955), -- Typická VS Code zelená pre komentáre
        bgColor = rgb(0x1E1E1E),
    },
    ["COMMENT LINE"] = {
        id = 2,
        fgColor = rgb(0x6A9955),
        bgColor = rgb(0x1E1E1E),
    },
    ["COMMENT DOC"] = {
        id = 3,
        fgColor = rgb(0x6A9955), -- JSDoc komentáre
        bgColor = rgb(0x1E1E1E),
    },
    ["COMMENT LINE DOC"] = {
        id = 15,
        fgColor = rgb(0x6A9955),
        bgColor = rgb(0x1E1E1E),
    },
    ["COMMENT DOC KEYWORD"] = {
        id = 17,
        fgColor = rgb(0x569CD6), -- Kľúčové slová v JSDoc (napr. @param) dostávajú modrú
        bgColor = rgb(0x1E1E1E),
        fontStyle = 1,
    },
    ["COMMENT DOC KEYWORD ERROR"] = {
        id = 18,
        fgColor = rgb(0xF44747), -- Výstražná červená pre chyby
        bgColor = rgb(0x1E1E1E),
    },
}
return L