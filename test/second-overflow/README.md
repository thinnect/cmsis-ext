# second-overflow

The second overflow test application checks that the 32-bit second counter
`osCounterGetSecond` does not overflow when the 32-bit millisecond counter
`osCounterGetMilli` overflows.

Instead of waiting for 49.7 days, when run with FreeRTOS, the initial tick value
is set to `-DconfigINITIAL_TICK_COUNT=0xfffff000`.

## build

`make tsb2`

## success
```
2020-08-03 20:00:57.001 : I|main:  95|secovrf 1.0.0-dev (1.0.0)
2020-08-03 20:00:57.004 : D|main:  34|app_loop
2020-08-03 20:00:57.006 : D|main:  46|ms=4294963201 s=4294963
2020-08-03 20:00:58.009 : D|main:  54|ms=4294964205 s=4294964
2020-08-03 20:00:59.012 : D|main:  54|ms=4294965208 s=4294965
2020-08-03 20:00:00.015 : D|main:  54|ms=4294966211 s=4294966
2020-08-03 20:00:01.019 : D|main:  54|ms=4294967214 s=4294967
2020-08-03 20:00:02.022 : D|main:  54|ms=921 s=4294968
2020-08-03 20:00:02.024 : I|main:  64|oveflow ok
```

## failure
```
2020-08-03 20:00:33.756 : I|main:  95|secovrf 1.0.0-dev (1.0.0)
2020-08-03 20:00:33.759 : D|main:  34|app_loop
2020-08-03 20:00:33.761 : D|main:  46|ms=4294963201 s=4294963
2020-08-03 20:00:34.762 : D|main:  54|ms=4294964204 s=4294964
2020-08-03 20:00:35.766 : D|main:  54|ms=4294965207 s=4294965
2020-08-03 20:00:36.769 : D|main:  54|ms=4294966210 s=4294966
2020-08-03 20:00:37.772 : D|main:  54|ms=4294967213 s=4294967
2020-08-03 20:00:38.775 : D|main:  54|ms=920 s=0
2020-08-03 20:00:38.777 : E|main:  60|OVERFLOW
```
