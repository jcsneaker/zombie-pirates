package de.bmw.ramses;

import android.content.Context;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class ResourceHelper {
    public static void writeRawResourceToFileIfNotExisting(Context context, int fileId, String targetFileName)
    {
        File file = new File(context.getFilesDir()+"/"+targetFileName);
        if (!file.exists()) {
            InputStream inputStream = context.getResources().openRawResource(fileId);
            byte[] buffer = new byte[4096];

            try {
                FileOutputStream outputStream = context.openFileOutput(targetFileName, Context.MODE_PRIVATE);

                int number_read = inputStream.read(buffer);
                while (number_read != -1) {
                    outputStream.write(buffer);
                    number_read = inputStream.read(buffer);
                }

                inputStream.close();
                outputStream.close();
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }
}
