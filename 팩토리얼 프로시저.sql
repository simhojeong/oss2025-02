DELIMITER //

CREATE PROCEDURE factProc()
BEGIN
    DECLARE n INT DEFAULT 5;
    DECLARE fact INT DEFAULT 1;
    DECLARE i INT DEFAULT 1;

    WHILE i <= n DO
        SET fact = fact * i;
        SET i = i + 1;
    END WHILE;

    SELECT '팩토리얼' AS 제목;
    SELECT '---------' AS 구분선;
    SELECT fact AS 결과값;
END;
//

DELIMITER ;

-- 실행
CALL factProc();
