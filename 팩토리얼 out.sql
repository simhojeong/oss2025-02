DROP PROCEDURE IF EXISTS pro5;
DELIMITER $$

CREATE PROCEDURE pro5(OUT result INT)
BEGIN
    DECLARE i INT DEFAULT 1;
    SET result = 1;

    WHILE i <= 5 DO
        SET result = result * i;
        SET i = i + 1;
    END WHILE;
END $$

DELIMITER ;

CALL pro5(@result);
SELECT @result;
