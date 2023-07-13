/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:51:17 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/10 13:51:29 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int hexCharToDecimal(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return -1;  // Invalid character
}

int hexStringToDecimal(const char *hexString) {
    int decimalNumber = 0;
    int i = 0;
    
    // Skip optional "0x" or "0X" prefix
    if (hexString[0] == '0' && (hexString[1] == 'x' || hexString[1] == 'X')) {
        i = 2;
    }
    
    while (hexString[i] != '\0') {
        int digit = hexCharToDecimal(hexString[i]);
        if (digit == -1) {
            // Invalid character encountered
            return -1;
        }
        decimalNumber = (decimalNumber * 16) + digit;
        i++;
    }
    
    return decimalNumber;
}

unsigned int atox(char *hex) {
    unsigned int val = 0;

    while (*hex) {
        // get current character then increment
        __uint8_t byte = *hex;
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
		printf("%c\n", *hex);
        if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		// else if (byte == 'x')
		// 	byte = byte - 'a';
        else if (byte >= 'a' && byte <='f')
			byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F')
			byte = byte - 'A' + 10;    
        // shift 4 to make space for new digit, and add the 4 bits of the new digit
        val = (val << 4) | (byte & 0xF);
		hex++;
    }
    return (val);
}