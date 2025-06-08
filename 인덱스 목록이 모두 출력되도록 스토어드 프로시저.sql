DROP PROCEDURE IF EXISTS pro2;
DELIMITER $$

CREATE PROCEDURE pro2(IN dbName VARCHAR(64), IN tableName VARCHAR(64))
BEGIN
    SET @sqlQuery = CONCAT('SHOW INDEX FROM ', dbName, '.', tableName);
    PREPARE stmt FROM @sqlQuery;
    EXECUTE stmt;
    DEALLOCATE PREPARE stmt;
END $$

DELIMITER ;

CALL pro2('world', 'city');
