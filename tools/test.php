<?php

// var_dump($argv);
// exit(0);
define("BUILD_TYPE", "Debug");
define("CASE_DELIMITER", "\n\n\n"); // Between test cases
define("PART_DELIMITER", "\n\n");   // Between code and expected output

$test_id = 0;
$passed = 0;
$failed = 0;
$total_time = 0;

function test($timeout = 0.5) {
    file_put_contents("test_p.gtc", $GLOBALS["src"]);

    $start_time = microtime(true);
    $output = shell_exec("timeout {$timeout}s ../".BUILD_TYPE."/gtlang_interprepter test_p.gtc");
    $end_time = microtime(true);

    $duration = $end_time - $start_time;
    $result = trim($output) === trim($GLOBALS["expected"]);

    return [$result, $duration, $output];
}

function check($num){
    if(!isset($GLOBALS["argv"][1]) ||$GLOBALS["argv"][1]==0){
        return true;
    }else {
        if ($num == $GLOBALS["argv"][1]) 
            return true;
        else
            return false;
    }
}
//===================================================

$test_file = file_get_contents("tests.gtt") ?: "";
$tmp1=explode("\n=========================================================================\n",$test_file);
$test_file_str = ($tmp1[0]);
// $test_file_str = preg_replace('/[ \t]+$/m', '', $test_file_str); // trim right spaces per line
$test_cases = explode(CASE_DELIMITER, trim($test_file_str));
$total_tests = count($test_cases);

if(!isset($argv[1]))
echo "=== RUNNING $total_tests TEST CASE(S) ===\n";

$line =1;
foreach ($test_cases as $test_case) {
    $test_id++;
    $line1=$line;
    $line += substr_count($test_case,"\n")+3;
    if(!check($test_id))
        continue;
    echo "\nTest #$test_id at line ${line1}: ";
    $parts = explode(PART_DELIMITER, $test_case, 2);
    $GLOBALS["src"] = $parts[0] ?? "";
    $GLOBALS["expected"] = $parts[1] ?? "";

    $res = test();
    $duration_ms = round($res[1] * 1000, 2);
    $total_time += $res[1];

    if ($res[0]) {
        $passed++;
        echo "✅ OK. ";
       } else {
        $failed++;
        echo "❌ FAILED!";
        if(isset($argv[1]))
            echo"\n=========\n{$GLOBALS["src"]}\n=========";
        echo "\n\tExpected:\n\t\t\"{$GLOBALS["expected"]}\"\n\tGot:\n\t\t\"" . trim($res[2]) . "\"\n";
    }

    echo "Time: {$duration_ms} ms\n";
}

$avg_time = $total_tests > 0 ? $total_time / $total_tests : 0;

if(!isset($argv[1])) {
    echo "\n=== SUMMARY ===\n";
    echo "✅ Passed: $passed\n";
    echo "❌ Failed: $failed\n";
    echo "🧪 Total: $total_tests\n";
    echo "⏱️ Total time: " . round($total_time, 4) . " s\n";
    echo "📊 Average time per test: " . round($avg_time * 1000, 2) . " ms\n";
}
//==============================================

$bench_file_str=($tmp1[1]);

$test_cases = explode(CASE_DELIMITER, trim($bench_file_str));
$total_tests = count($test_cases);

if(!isset($argv[1]))
echo "=== RUNNING $total_tests BENCH CASE(S) ===\n";

$line -=1;
foreach ($test_cases as $test_case) {
    $test_id++;
    $line1=$line;
    $line += substr_count($test_case,"\n")+3;
    if(!check($test_id))
        continue;
    echo "\nTest #$test_id at line ${line1}: ";
    $parts = explode(PART_DELIMITER, $test_case, 2);
    $GLOBALS["src"] = $parts[0] ?? "";
    $GLOBALS["expected"] = $parts[1] ?? "";

    $res = test(30);
    $duration_ms = round($res[1] * 1000, 2);
    $total_time += $res[1];

    if ($res[0]) {
        $passed++;
        echo "✅ OK. ";
       } else {
        $failed++;
        echo "❌ FAILED!";
        if(isset($argv[1]))
            echo"\n=========\n{$GLOBALS["src"]}\n=========";
        echo "\n\tExpected:\n\t\t\"{$GLOBALS["expected"]}\"\n\tGot:\n\t\t\"" . trim($res[2]) . "\"\n";
    }

    echo "Time: {$duration_ms} ms\n";
}
