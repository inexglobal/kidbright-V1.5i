module.exports = function(Blockly){
  'use strict';



Blockly.Blocks['eeprom_read'] = {
  init: function() {
    this.appendValueInput("address")
        .setCheck("Number")
        .appendField("EEPROM read from address");
    this.setInputsInline(true);
    this.setOutput(true, "Number");
    this.setColour(45);
 this.setTooltip("EEPROM read (address : 0 to 127)");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['eeprom_write'] = {
  init: function() {
    this.appendValueInput("address")
        .setCheck("Number")
        .appendField("EEPROM address");
    this.appendValueInput("value")
        .setCheck(["Number"])
        .appendField("write value");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(45);
 this.setTooltip("EEPROM write (address : 0 to 127 , value : 0 to 255)");
 this.setHelpUrl("");
  }
};



}