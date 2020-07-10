module.exports = function(Blockly){
  'use strict';



Blockly.JavaScript['eeprom_read'] = function(block) {
  var value_address = Blockly.JavaScript.valueToCode(block, 'address', Blockly.JavaScript.ORDER_ATOMIC);  
  var code = `rtc.getEepromByte(${value_address})`;
  return [code, Blockly.JavaScript.ORDER_ATOMIC];
};

Blockly.JavaScript['eeprom_write'] = function(block) {
  var value_address = Blockly.JavaScript.valueToCode(block, 'address', Blockly.JavaScript.ORDER_ATOMIC);
  var value_value = Blockly.JavaScript.valueToCode(block, 'value', Blockly.JavaScript.ORDER_ATOMIC);  
  var code = `rtc.setEepromByte(${value_address},${value_value});\n`;
  return code;
};


}