tests_folder=tests
prog=motcache
help_first_line="Usage: ./motcache <TEXTFILE>"

@test "test0 : Aucun argument" {
    run ./$prog
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "nombre arguments invalide" ]
    [ "${lines[1]}" = "$help_first_line" ]
}

@test "test1 : Test fourni" {
    run ./$prog $tests_folder/MANDOLINE.txt
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "MANDOLINE" ]
}
