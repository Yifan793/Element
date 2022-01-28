function isNotLoop() {
    let isLoop = root.elements.isLoop.isChecked
    return !isLoop
}

function isAttrEnabled() {
    return root.elements.attrEnabled.isChecked
}

function isUvAnimEnabled() {
    return root.elements.uvAnimEnabled.isChecked
}

function isComboboxSelect(value)
{
    return root.elements.shape.comboBox.getCurValueByRole("value") === value
}
