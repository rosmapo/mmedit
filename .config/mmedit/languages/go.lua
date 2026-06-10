local L = {}

L.lexer = "cpp"

L.singleLineComment = "// "

L.extensions = {
    "go",
}

L.properties = {
    ["fold.cpp.comment.explicit"] = "0",
    ["lexer.cpp.track.preprocessor"] = "0",
    ["lexer.cpp.escape.sequence"] = "1",
}

L.keywords = {
    [0] = "bool byte break case chan complex64 complex128 const continue defer default else for func go goto fallthrough false float32 float64 if import int interface int8 int16 int32 int64 len map nil package range return select string struct switch true type uint uintptr uint8 uint16 uint32 uint64 var",
    [5] = "FIXME TODO XXX HACK NOTE",
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
    ["TASK MARKER"] = {
        id = 26,
        fgColor = rgb(0x6A9955),
        bgColor = rgb(0x1F1F1F),
        fontStyle = 1,
    },
}
return L
