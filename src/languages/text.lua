local L = {}

L.name = "Text"

L.lexer = "null"

L.disableFoldMargin = true

L.extensions = {
    "",
    "txt",
}

L.styles = {
    ["DEFAULT"] = {
        id = 0,
        fgColor = rgb(0xD4D4D4),
        bgColor = rgb(0xFFFFFF),
        fontStyle = 0,
    },
}

return L
