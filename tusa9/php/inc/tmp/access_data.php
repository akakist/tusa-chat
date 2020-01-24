<?
    function get_fio($id)
    {
	fio=mysql_select1("select fname, ' ', lname from tbl_users ")
    }
?>