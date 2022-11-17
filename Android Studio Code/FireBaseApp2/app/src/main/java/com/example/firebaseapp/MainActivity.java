package com.example.firebaseapp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.Button;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {
    private Button button;
    private Button button2;
    private Button button3;
    private Button button5;
    private Button button6;

    private TextView textView2;
    private TextView textView4;
    private TextView textView6;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button= findViewById(R.id.button);
        button2= findViewById(R.id.button2);
        button3= findViewById(R.id.button3);
        button5= findViewById(R.id.button5);
        button6= findViewById(R.id.button6);

        textView2=findViewById(R.id.textView2);
        textView4=findViewById(R.id.textView4);
        textView6= findViewById(R.id.textView6);


        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                config();
            }
        });
        button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Monitor();
            }
        });
        button5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Manual();
            }
        });
        button6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                textView6.setText("ON");
            }
        });
        FirebaseDatabase database=FirebaseDatabase.getInstance();
        DatabaseReference myRef=database.getReference().child("Day1");

        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                String counter = snapshot.child("Fert_A").getValue().toString();
                textView2.setText(counter);
            }
            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
        //load
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                myRef.child("Day1").setValue(1);
            }
        });
    }
    public void config(){
        Intent intent=new Intent(this, MainActivity2.class);
        startActivity(intent);
    }
    public void Monitor(){
        Intent intent=new Intent(this, MainActivity3.class);
        startActivity(intent);
    }
    public void Manual(){
        Intent intent=new Intent(this, MainActivity3.class);
        startActivity(intent);
    }

}