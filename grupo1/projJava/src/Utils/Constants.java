package Utils;

import java.util.regex.Pattern;

public class Constants {

    public static final int N_MONTHS = 12;
    public static final int N_BRANCHES = 3;
    public static final int N_TYPES = 2;
    public static final int N = 0;
    public static final int P = 1;
    public static final Pattern clientPattern = Pattern.compile("[A-Z]([0-4]\\d{3}|50{3})");
    public static final Pattern productPattern = Pattern.compile("[A-Z][A-Z]([0-4]\\d{3}|50{3})");
}
